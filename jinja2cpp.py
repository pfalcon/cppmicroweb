import sys
import re

import jinja2
import jinja2.meta
from jinja2 import nodes
from jinja2.nodes import *
from jinja2.compiler import CodeGenerator, CompilerExit, Frame
from jinja2.ext import Extension


class ArgStmtExtension(Extension):

    tags = set(['arg'])

    def parse(self, parser):
        token = next(parser.stream)
        tokens = []
        while parser.stream.current.type != 'block_end':
            tokens.append(next(parser.stream).value)
#        print tokens
        node = parser.free_identifier(lineno=token.lineno)
        node.name = ("".join(tokens[:-1]).encode("utf8"), tokens[-1])
        return node


class MyCodeGenerator(CodeGenerator):

    def __init__(self, *args, **kwargs):
        CodeGenerator.__init__(self, *args, **kwargs)
        self.args = {}

    def visit_Template(self, node, frame=None):
        self.writeline('#include "microweb.hpp"')
        #self.writeline("using namespace std;")
        self.writeline("")
        self.writeline("void %s(ostream& out" % self.name)
        comma = True
        for argnode in node.find_all(InternalName):
            type, name = argnode.name
            self.args[name] = type
            if comma:
                self.write(", ")
            self.write("const " + type + "& " + name)
            comma = True
        self.write(")")

        have_extends = node.find(nodes.Extends) is not None
        eval_ctx = EvalContext(self.environment, self.name)
        frame = Frame(eval_ctx)
        frame.inspect(node.body)
        frame.toplevel = frame.rootlevel = True
        frame.require_output_check = have_extends and not self.has_known_extends

        self.writeline("{")
        self.indent()
        self.blockvisit(node.body, frame)
        self.outdent()
        self.writeline("}")
        self.writeline("")

    def visit_For(self, node, frame):
#        print node
        iter_var = node.target.name
        seq_var = node.iter.name
        seq_type = self.args[seq_var]
        seq_container, item_type = self.parse_container_type(seq_type)
        self.writeline("for (const %s& %s: %s) {" % (item_type, iter_var, seq_var))
        self.indent()
        self.blockvisit(node.body, frame)
        self.outdent()
        self.writeline("}")
#        print list(node.iter_child_nodes())

    def visit_Output(self, node, frame):
        body = []
        for child in node.nodes:
            try:
                const = child.as_const(frame.eval_ctx)
                body.append(const)
            except:
                body.append(child)
        self.writeline("out")
        for item in body:
            self.write(" << ")
            if type(item) == type(u""):
                self.write(self.c_string(item))
            else:
                self.visit(item, frame)
        self.write(";")

    def visit_Call(self, node, frame, forward_caller=False):
        self.visit(node.node, frame)
        self.write('(')
        extra_kwargs = forward_caller and {'caller': 'caller'} or None
        self.signature(node, frame, extra_kwargs)
        self.write(')')

    def visit_Getattr(self, node, frame):
        self.visit(node.node, frame)
        self.write("." + node.attr)

    def visit_TemplateData(self, node, frame):
#        self.write(repr(node.as_const(frame.eval_ctx)))
        1 / 0
        print "hello"
        return "!!!!!!!!!!!!!!!"

    def visit_Name(self, node, frame):
        if node.ctx == 'store' and frame.toplevel:
            frame.toplevel_assignments.add(node.name)
        self.write(node.name)
        frame.assigned_names.add(node.name)

    def visit_InternalName(self, node, frame):
#        type, name = node.name
#        self.args[name] = type
#        print self.args
        pass

    def signature(self, node, frame, extra_kwargs=None):
        comma = False
        for arg in node.args:
            if comma:
                self.write(', ')
            self.visit(arg, frame)
            comma = True

    def blockvisit(self, nodes, frame):
        try:
            for node in nodes:
                self.visit(node, frame)
        except CompilerExit:
            pass


    def c_string(self, s):
        s = repr(s.encode("utf8"))
        s = s[1:-1]
        return '"' + s + '"'

    def parse_container_type(self, type):
        m = re.match(r"(.+)<(.+)>$", type)
        assert m
        return m.group(1), m.group(2)

#    def write(self, sth):
#        sys.stdout.write(sth)


env = jinja2.Environment(extensions=[ArgStmtExtension])

tpl = open(sys.argv[1])
ast = env.parse(tpl.read())
#print ast

tpl_name = sys.argv[1].rsplit('.', 1)[0]
codegen = MyCodeGenerator(ast.environment, tpl_name, sys.argv[1])
codegen.stream = sys.stdout
codegen.visit(ast)
