#!/usr/bin/env python
# -*- coding: utf-8 -*-

import argparse
from pyparsing import Word, OneOrMore, alphas

def funcname(letter):
    """The name of the generated functions in the output."""
    return "morse_" + letter

def parse_morse_letter(line):
    """Parse a line of input from the morse code table file and convert it into a parsetree."""
    letter = Word(alphas)
    token = Word(alphas)
    morse_letter_expression = letter.setResultsName('letter')\
                            + OneOrMore(token).setResultsName('tokens')
    return morse_letter_expression.parseString(line)

def funcarray(parsetree):
    """Generate the array of function pointers."""
    fmtstr = "void (*alphabet[])() = {{ {} }};"
    funcnames = set(e.letter for e in parsetree);
    return fmtstr.format(', '.join("&"+funcname(f) for f in sorted(funcnames)))
    
def letterfunc(letter_def):
    """Generate a function for a single letter."""
    func_fmtstr = "void {name}() "\
                + "{{ token_count = 0; {tokens} tokens[token_count++] = &interletter;}};"
    token_fmtstr = "tokens[token_count++] = &{};"
    fmtargs = {
        'name': funcname(letter_def.letter),
        'tokens': " ".join(token_fmtstr.format(t) for t in letter_def.tokens)
    }
    return func_fmtstr.format(**fmtargs)

def autogen(infile):
    """Generate all the code from the morse code table file."""
    parsetree = [parse_morse_letter(l) for l in infile.readlines()]
    generated = '\n'
    for l in parsetree:
        generated += letterfunc(l) + '\n'
    generated += "\n\n"
    generated += funcarray(parsetree) + '\n'
    return generated

def inject(template_file, injection, delimiter = "// --autogen--"):
    """Supplant everything in *injection* into the *original* string between the pair of
       *delimiters*"""
    before, inside, after = template_file.read().split(delimiter)
    return before + delimiter + injection + delimiter + after

def cmdargs():
    """Handle the command line arguments."""
    argparser = argparse.ArgumentParser()
    argparser.add_argument('-i', '--input', dest='input', type=str, required=True)
    argparser.add_argument('-t', '--template', dest='template', type=str, required=True)
    args = argparser.parse_args()
    return open(args.input, 'r'), open(args.template, 'r')

if __name__ == '__main__':
    infile, template = cmdargs()
    generated = autogen(infile)
    print inject(template, generated)