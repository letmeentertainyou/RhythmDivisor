from setuptools import Extension
from setuptools import setup

module = Extension(
    "rhythm",
    sources=["array.c", "rhythm.c"],
    extra_compile_args=["-Wall"],
)

setup(
    name="rhythm",
    version="0.1.0",
    description="A C Python version of rhythm.py.",
    url="https://github.com/letmeentertainyou/RhythmDivisor",
    author="Lars S",
    author_email="",
    license="MIT",
    classifiers=[
        "Programming Language :: Python :: 3",
    ],
    ext_modules=[module],
)
