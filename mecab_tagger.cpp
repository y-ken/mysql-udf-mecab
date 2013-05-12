extern "C" {
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
}
#include <mecab.h>

extern "C" {
my_bool mecab_wakati_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
void mecab_wakati_deinit(UDF_INIT *initid);
char *mecab_wakati(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *ret_length, char *is_null, char *error);
}

my_bool mecab_wakati_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1)
  {
    strcpy(message,"Wrong arguments to mecab_wakati;  must be (str)");
    return 1;
  }

  if ( args->arg_type[0] != STRING_RESULT ) {
    args->arg_type[0] = STRING_RESULT;
  }
  return 0;
}

void mecab_wakati_deinit(UDF_INIT *initid)
{
  if (initid->ptr)
    free(initid->ptr);
}

char *mecab_wakati(UDF_INIT *initid, UDF_ARGS *args, char *result,
                  unsigned long *ret_length, char *is_null, char *error)

{
  const char *input;
  unsigned long len;
  size_t   rlen;

  input = args->args[0];
  len = args->lengths[0];

  if (len <= 0  ||  args->arg_type[0] != STRING_RESULT )
  {
    *is_null=0;
    *ret_length = 0;
    return 0;
  }

  if (!args || !args->args[0])
  {
    *is_null=1;
    *ret_length = 0;
    return 0;
  }

  if ( len < 1)  { len=1; }

  if (!( result = (char*) malloc( sizeof(MeCab::Tagger)) ) )
  {
    /* strmov(message,"Couldn't allocate memory in mecab_tagger_init"); */
    *is_null=1;
    *error=1;
    *ret_length = 0;
    return 0;
  }

  if (initid->ptr) free(initid->ptr);

  MeCab::Tagger *tagger = MeCab::createTagger("-Owakati");
  const char *output = tagger->parse(input);

  rlen = strlen(output);
  while (rlen > 0 && (output[rlen-1] == ' ' || output[rlen-1] == '\n'))
    rlen--;

  char result2[strlen(output)];
  memcpy(result2, &output[0], rlen);
  *ret_length = rlen;
  result = result2;

  delete tagger;
  return result;
}
