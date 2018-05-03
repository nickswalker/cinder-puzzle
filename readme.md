# cinder-puzzle

A framework for using the powerful [clingo](https://potassco.org/clingo/) ASP solving system within the [Cinder](https://libcinder.org/)
creative coding environment. It provides tools for

* loading and solving existing answer set programs
* constructing answer set programs dynamically
* managing solve execution
* parsing the results

## Development

cinder-puzzle links against libclingo and cinder. Build both from sources and place them in cinder-puzzle's parent directory.

Pull down the clingo and cinder submodules with

    git clone --recursive https://github.com/nickswalker/cinder-puzzle.git

Build these dependencies.

    cd clingo
    mkdir build
    cd build
    cmake ..
    make -j8
    cd ../cinder
    mkdir build
    cd build
    cmake ..
    make -j8

## Usage

The API is fluctuated as development continues. Look under `src/demos` for full, up-to-date usage examples.

Once the dependencies are built, you can build the demos.

    mkdir build
    cmake ..
    make

## Troubleshooting

### "Ignoring Xlib error" messages

Comment out `fprintf(stderr, "Ignoring Xlib error: error code %d request code %d\n", err->error_code, err->request_code);` in
`Cinder/src/AntTweakBar/TwMgr.cpp`.
See [this thread](https://github.com/cinder/Cinder/issues/1865) for more information.

### Segfault on demo launch

Build with system Boost. See [this issue](https://github.com/cinder/Cinder/issues/1799) for more information.

    cmake .. -DCINDER_BOOST_USE_SYSTEM=1
    make