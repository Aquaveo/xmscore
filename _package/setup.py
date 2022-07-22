"""
Setup.py file for the xms.core python package.
"""
import os

from setuptools import setup

from xms.core import __version__


# allow setup.py to be run from any path
os.chdir(os.path.normpath(os.path.join(os.path.abspath(__file__), os.pardir)))

requires = [
    'numpy',
]


version = __version__

setup(
    python_requires='>=3.10',
    name='xmscore',
    version=version,
    packages=['xms.core', 'xms.core.filesystem', 'xms.core.misc', 'xms.core.time'],
    include_package_data=True,
    license='BSD 2-Clause License',
    description='',
    author='Aquaveo',
    install_requires=requires,
    package_data={'': ['*.pyd', '*.so']},
    test_suite="tests",
)
