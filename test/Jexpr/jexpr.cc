
#include "parser.h"
#include "exprs.h"

int usage(const char* arg0)
{
  using namespace std;

  cout << "\nUsage: " << arg0 << " (switches) infile.j\n\n";
  cout << "Analyze a Java assembly file. Valid switches:\n";
  cout << "\n";
  cout << "\t-j: Output a stripped .j file.\n";
  cout << "\t-m method: Restrict output to one method.\n";
  cout << "\t-T: Show more type information.\n";
  cout << "\t-t: Show less type information (default).\n";
  cout << "\t-V: With versioning for variables.\n";
  cout << "\t-v: Without versioning for variables (default).\n";
  cout << "\t-x: Examine expressions.\n";
  cout << "\n";
  cout << "Options -j and -x cancel each other out.\n";
  cout << "Reads from standard input if no input file is given.\n\n";

  return 1;
}

int main(int argc, const char** argv)
{
  const char* infile = 0;
  char outtype = 'x';
  const char* method = 0;

  expr::setShowTypes(false);
  expr::setShowVersion(false);

  /*
    Parse command line
  */
  for (int i=1; i<argc; i++) {
    if ('-' != argv[i][0]) {
      // must be the input file
      if (infile) return usage(argv[0]);
      infile = argv[i];
      continue;
    }
    // must be a switch
    if (0 != argv[i][2]) {
      std::cerr << "Unknown switch: " << argv[i] << "\n";
      std::cerr << "Run without arguments for usage.\n";
      return 1;
    }
    switch (argv[i][1]) {
      case 'j':
      case 'x':
                outtype = argv[i][1];
                continue;

      case 'm':
                method = argv[i+1];
                i++;
                continue;

      case 't':
      case 'T':
                expr::setShowTypes('T' == argv[i][1]);
                continue;
                
      case 'v':
      case 'V':
                expr::setShowVersion('V' == argv[i][1]);
                continue;
                
      default:  std::cerr << "Unknown switch: " << argv[i] << "\n";
                std::cerr << "Run without arguments for usage.\n";
                return 1;
    }
  }

  dotjfile* J = parse(infile);
  if (0==J) return 1;

  if ('j' == outtype) {
    J->writeDotj(std::cout, method, false);
  } else {
    J->writeExprs(std::cout, method);
  }
  return 0;
}
