#include <time.h>
#include <nan.h>

using v8::FunctionTemplate;
const char *ERROR_NumberOfArguments = "Wrong number of arguments";
const char *ERROR_TypeError = "Wrong type of argument";
char error_message[100];

#define check_argc(argc) \
  if (info.Length() != argc) \
    { Nan::ThrowError(ERROR_NumberOfArguments); return; }

#define check_type(check) \
  if(!(check)) \
    { Nan::ThrowTypeError(ERROR_TypeError); return; }

#define arg_number(idx) \
  info[idx]->NumberValue(Nan::GetCurrentContext()).ToChecked()

#define ThrowErrorFormated(...) \
  snprintf( error_message, sizeof(error_message), __VA_ARGS__ ); \
  Nan::ThrowError(error_message)

#define method(name,function) \
  Nan::Set(target, Nan::New(name).ToLocalChecked(), \
    Nan::GetFunction(Nan::New<FunctionTemplate>(function)).ToLocalChecked())

NAN_METHOD(microsleep)
  {
    check_argc(1);
    check_type(info[0]->IsNumber());
    struct timespec time;

    long long value = arg_number(0) * 1000LL;
    time.tv_sec  = value / 1000000000LL;
    time.tv_nsec = value % 1000000000LL;
    if (nanosleep(&time, NULL))
      {
        ThrowErrorFormated("Error when sleeping: %s", strerror(errno));
        return;
      }
  }

NAN_MODULE_INIT(InitAll) {
  method("microsleep",microsleep);
}

NODE_MODULE(sleep, InitAll)
