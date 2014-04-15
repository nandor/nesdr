// This file is part of the gbdyn project
// Licensing information can be found in the LICENSE file
// (C) 2013 Licker Nandor. All rights reserved.
#include "emu.h"

void
Emulator::Init(const std::string& file)
{
  mem.LoadINes(file);
  //mem.LoadBank(0, Memory::LROM);
  //mem.LoadBank(1, Memory::HROM);
  mem.LoadBank(0, Memory::HROM);
  cpu.Start();
}

void
Emulator::Run()
{
  for (int i = 0; i < 300; ++i)
  {
    cpu.Tick();
  }
}

void
Emulator::Destroy()
{

}

void
Emulator::Usage(std::ostream& os)
{
  os << "Usage: nesdr rom.nes [options]                 \n";
  os << "Options:                                       \n";
  os << "  --debug:     Enable debugging                \n";
  os << "  --verbose:   Print detailed information      \n";
}

void
Emulator::Main(int argc, char **argv)
{
  const char *input = 0;
  int c, option_idx = 0;

  static struct option options[] =
  {
    { "debug",   no_argument,       &debug,    1 },
    { "verbose", no_argument,       &verbose,  1 },
    { 0,         0,                 0,         0 }
  };

  while ((c = getopt_long_only(argc, argv, "", options, &option_idx)) != -1)
  {
    switch (c)
    {
      case '?':
      {
        Usage(std::cerr);
        return;
      }
    }
  }

  if (optind + 1 != argc)
  {
    Usage(std::cout);
    return;
  }

  Init(argv[optind]);
  Run();
  Destroy();
}

int
main(int argc, char **argv)
{
  try
  {
    (Emulator()).Main(argc, argv);
    return EXIT_SUCCESS;
  }
  catch (std::exception& e)
  {
    std::cerr << "ERROR: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
