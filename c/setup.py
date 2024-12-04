#!/usr/bin/env python

from setuptools import setup, Extension

module = Extension('condorcet', sources=['condorcet.c'])

setup(
    name='Condorcet',
    version='1.0',
    description='Condorcet method implemented in C',
    ext_modules=[module]
)
