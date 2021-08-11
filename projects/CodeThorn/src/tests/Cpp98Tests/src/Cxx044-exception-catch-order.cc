#include <setjmp.h>

#include "test-new.h"
#include "test-main.h"

const char* description = "Compares various subobjects of a class";
const char* expectedout = "{ExATWSswtTWSExExA~ExA~Ex~ExA~Ex}";


struct Ex
{
  Ex()
  : data("Ex")
  {
    printf("Ex");
  }

  Ex(const char* desc)
  : data(desc)
  {}

  ~Ex() { printf("~Ex"); }

  const char* data;
};

struct ExA : Ex
{
  ExA()
  : Ex("ExA")
  {
    printf("ExA");
  }

  ~ExA() { printf("~ExA"); }
};


void service(const ExA* ex)
{
  printf("S");
  if (ex) throw *ex;
  printf("s");
}


void work(const ExA* ex)
{
  printf("W");
  service(ex);
  printf("w");
}

void test(const ExA* escape)
{
  try
  {
    printf("T");
    work(escape);
    printf("t");
  }
  catch (const Ex& ex)
  {
    printf("Ex%s", ex.data);
  }
  catch (const ExA& ex)
  {
    printf("ExA%s", ex.data);
  }
  catch (...)
  {
    printf("?");
  }
}

void run()
{
  ExA exa;

  test(NULLPTR);
  test(&exa);
}

