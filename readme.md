# tempora

Utility for retrieving directories for temporary file storage.

## Documentation

You'll find the latest documentation at [tempora.think-biq.com](https://tempora.think-biq.com).

## Example

See [examples/read.c](examples/read.c) for a full example.

```c
tempora_temp_dir_type_t t = tempora_read(path, TEMPORA_PATH_SIZE);
printf("Temp path: %s (type: %s)\n", path, tempora_dir_type_name(t));
```