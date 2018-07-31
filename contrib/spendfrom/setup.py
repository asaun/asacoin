from distutils.core import setup
setup(name='asaspendfrom',
      version='1.0',
      description='Command-line utility for asacoin "coin control"',
      author='Gavin Andresen',
      author_email='gavin@asacoinfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
