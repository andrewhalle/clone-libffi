#include <stdlib.h>
#include <stdio.h>
#include "./ffi.h"

void init_callable(callable *c) {
  c->args = (int*) malloc(16 * sizeof(int));
  c->n_args = 0;
}

void add_arg_callable(callable *c, int arg) {
  c->args[c->n_args] = arg;
  c->n_args++;
}

void ffi_closure_alloc(void) {}
void ffi_closure_free(void) {}

ffi_status ffi_prep_cif(
  ffi_cif *cif,
  ffi_abi abi,
  unsigned int nargs,
  void *ignored1,
  void *ignored2
) {
  cif->n_args = nargs;
  return FFI_OK;
}

void ffi_call(ffi_cif *cif, void *fn, void *retval, void **args) {
  unsigned int n_args = cif->n_args;
  cif->func = fn;
  init_callable(cif);

  // actually add the arguments to the callable
  for (int i = 0; i < n_args; i++) {
    add_arg_callable(cif, *((int*) args[i]));
  }

  runtime_call((void*) cif, retval);
}

void ffi_prep_closure_loc(void) {}
