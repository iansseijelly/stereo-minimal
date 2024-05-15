# setup.py
from setuptools import setup, Extension
from Cython.Build import cythonize
import numpy as np

extensions = [
    Extension(
        "disparity", 
        sources=["disparity.pyx", "disparity_source.c"],
        include_dirs=[np.get_include()]
    )
]

setup(
    name="Disparity Module",
    ext_modules=cythonize(extensions, language_level="3"),
)

