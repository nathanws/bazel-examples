Example of using https://github.com/nlohmann/json with Bazel.

Look at the [WORKSPACE](WORKSPACE) and [json.BUILD](json.BUILD) files to see
how the library is included.

Look at the [BUILD](main/BUILD) file to see how the dependency is added.

### Building

From the project root, run:

```
bazel build //main:roster
```

### Running

After building, from the project root run:

```
./bazel-bin/main/roster -helpmatch main
```
