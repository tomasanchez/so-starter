# Advanced OS Assignment Making

- [Advanced OS Assignment Making](#advanced-os-assignment-making)
	- [Intro](#intro)
	- [Getting Started](#getting-started)
		- [Environment Set Up](#environment-set-up)
		- [Installation](#installation)
		- [Openning the project](#openning-the-project)
			- [Workflows](#workflows)
			- [Makefile](#makefile)
			- [Creating your Module](#creating-your-module)
			- [Launching Options](#launching-options)
	- [Going Further](#going-further)
		- [Versioning](#versioning)
			- [Project Package](#project-package)
			- [Signature](#signature)
			- [Commiting](#commiting)
			- [Commit types](#commit-types)
		- [Testing](#testing)
			- [Implementation](#implementation)
			- [Skipping tests](#skipping-tests)
			- [More complex tests](#more-complex-tests)
	- [License](#license)
	- [Credits](#credits)

## Intro

This Book is the Property of the ~~Half-Blood~~ Half-Coder Prince.

![Advances OS Making](https://static.wikia.nocookie.net/harrypotter/images/b/b9/Advanced_Potion_Making..png/revision/latest?cb=20210822080741)

Inspired by Harry Potter's World, In which [Severus Snape makes importants anotattions]((https://harrypotter.fandom.com/wiki/Severus_Snape%27s_copy_of_Advanced_Potion-Making)) for improvements over a study book. I decided to develop my own implementation for the Operating System Course Assignment.

## Getting Started

I will assume you already have a  **GitHub account**, a team with at least **Two and a Half** ~~Men~~ **Programmers**.

### Environment Set Up

- [Virtual Box](https://www.virtualbox.org/wiki/Downloads): download the latest version.
- [Ubuntu Server v5.0.1](https://www.utnso.com.ar/recursos/maquinas-virtuales/): download the corresponding server version provided by UTNSO.
- ~~Lubuntu v5.0.1 Recommended Enviroment~~  [Ubuntu](https://ubuntu.com/download/desktop) or [Mint](https://linuxmint.com/download.php): download latest 64-bit LTS version.
- ~~Eclipse~~ VsCode: download the latest version.
  - Install the following extensions
    - [Git Lense](https://marketplace.visualstudio.com/items?itemName=eamodio.gitlens): git expansion.
    - [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools): Language support, featuring IntelliSense and Debugging.
    - [Doxygen Documentation Generator](https://marketplace.visualstudio.com/items?itemName=cschlosser.doxdocgen): for documentation.
    - [C-Mantic](https://marketplace.visualstudio.com/items?itemName=tdennis4496.cmantic): Source actions, including refactoring and code generation.
    - [Editor Config](https://marketplace.visualstudio.com/items?itemName=EditorConfig.EditorConfig): standarize your team formatting options.
    - [Better Comments](https://marketplace.visualstudio.com/items?itemName=aaron-bond.better-comments): more human-friendly comments

### Installation

I highly recommend running your `Ubuntu` or `Mint` native. The server **must** be run on `VBox` or any other virtualization product.

Once on your environment OS, you **must** install the following dependencies:

With `CTRL` + `ALT` + `T` you can open a Terminal.

Paste the following commands:

```
sudo apt-get update
sudo apt-get upgrade -y
sudo apt-get install git build-essential valgrind bison flex
sudo snap install code --classic
```

This will install you the necessary tools to build your project, indluding git, make and valgrind.

Now clear your terminal

```
clear
```

And  Clone the starter repository and install the dependencies (commons and readline). Paste the following commands:

```
mkdir -p Dev
cd Dev
git clone https://github.com/tomasanchez/so-starter.git
cd so-starter
sudo make install
```

With this you are all set.

### Openning the project


```
cd Dev/so-starter
code .
```

This should open `VsCode` in the `so-start` directory.

Run

```
make test
```

If you obtain

```
RESULTS: X tests (X ok, 0 failed, 0 skipped) ran in Y ms
Tests completed.
```

Then everything is working correctly.

I highly recommend configuring format on paste, on save and on type, to maintain a formatted file.

There too many directories! However, it is easy to understand.

1. `.github`: [Workflows](#workflows) actions for Continuous Integration.
2. `.vscode`: [Launching options](#launching-options) and other `Code` configurations.
3. `build`: Executables files will be placed here.
4. `config`: Configuration directory container, all `.cfg` files should be placed in here.
5. `lib`: Shared library module, for sharing functionalities among modules.
6. `shard`: All Shared objects (`*.o` files) are stored here.
7. `client`: a module implementation example  of the TP0 client.
8. `server`: a module implementation example of the TP0 server.


#### Workflows

GitHub Actions jobs can be automatically triggered, where they run, and how they can interact with the code in your repository. This starter has a job for testing the project. Each module will execute defined test.

This workflow will allow you to use Continuous Integration in your project, when `push` or `pull request` on main branch.

If all test passed, you will see a :heavy_check_mark: in the top. Otherwise, a :x: will be displayed. So when pull request are created, your team can easily `approve/reject` the pull request, checking not only merge conflicts but test passed.


#### Makefile

The `Makefile` in the root directory is used to build a project with different modules.

The following commands are available

1. make install
2. make test
3. make YOUR_MODULE_NAME

You should modifythe following rules, and add new ones as explained below:

This starter includes two modules, server and client. Which is a solution for [UTN FRBA OS-Course TP0](https://docs.google.com/document/d/1wBsTIlPc_4UKyHRUVxoY3VIepBO_tMq9CNqz3wGoGlA/edit).

This snippet displays the modules directories names.

```shell
# Modules directories - with their own makefile
SERVER_DIR=server
CLIENT_DIR=client
```
Then below:

```shell
.PHONY: server client clean install test install-commons

# Directories list
DIRS = $(SERVER_DIR) $(CLIENT_DIR)

client:
	cd $(CLIENT_DIR) && $(MAKE_COMPILE)

server:
	cd $(SERVER_DIR) && $(MAKE_COMPILE)
```

When creating your own module you **MUST** declare it in this `Makefile`.

suppose, you add a `Memory` module, in a directory `/memory`, then your `Makefile` should look like this

```shell
# Modules directories - with their own makefile
SERVER_DIR=server
CLIENT_DIR=client
MEMORY_DIR=memory
```

```shell
.PHONY: server client memory clean install test install-commons

# Directories list
DIRS = $(SERVER_DIR) $(CLIENT_DIR)

client:
	cd $(CLIENT_DIR) && $(MAKE_COMPILE)

memory:
	cd $(MEMORY_DIR) && $(MAKE_COMPILE)

server:
	cd $(SERVER_DIR) && $(MAKE_COMPILE)
```

The keyword `MEMORY_DIR` has been added with the value of your directory name `memory`.

`.PHONY` has been modified, adding `memory` after `client`.

`memory` rule has been added, just paste any of the client or server rules and change the `$(DIRECTORY)`

**NOTE**: About copying & pasting `Makefile`, make sure to set up a `.editorconfig` in your root folder with the following configuration

```properties
# top-most EditorConfig file
root = true

[*]
indent_style = tab
indent_size = 4
end_of_line = lf
charset = utf-8
trim_trailing_whitespace = true
insert_final_newline = true
```

The important is to set `indent_style` to `tab` otherwise makefile could result in the following error:

```shell
makefile:13: *** missing separator.  Stop.
```

It is recommend to

```shell
cp Makefile DESTINATION_PATH
```

Where `DESTINATION_PATH` is the path where the Makefile will be copied.

#### Creating your Module

You can easily create your module copying an example module, and modifying the root `Makefile` as shown [above](#makefile).

```shell
cp -r client memory
```

**OR** copy the server...

```shell
cp -r server memory
```

Then when inside the `memory` directory, run:

```shell
make run
```

This will `compile` the module creating a `memory.out` executable in `/build`, and execute it. To test your module you should run:

```shell
make test
```

This will run the test defined in `/memory/test`, creating a `memory_out.out` executable.

**NOTE**: the naming of the directory determines the name of the `.out` file.
Eg. `/example` module will create a `/build/example.out.` and a `/build/example_test.out` files.

#### Launching Options

For debugging using `VsCode`, a `launch.json` should be defined inside `.vscode` directory.

This template contains already a `launch.json` file, I recommend coyping the configurations and modifying for corresponding executables.

```json
{
      "name": "Example",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/build/example.out",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${workspaceFolder}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "gdb",
      "setupCommands": [
        {
          "description": "Enable pretty-printing for gdb",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ]
},
```

By only modifying `"name": "Your_Module_Name` and `"program":"${workspaceFolder}/build/YOUR_MODULE_NAME.out"`, for debugging test you should add another configuration, changing also `"name"` with `Your_Moodule_Name TEST` and `"program"` with `YOUR_MODULE_NAME_test.out` value.

Eg. of a A full `launch.json` with the `memory` module.

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Memory",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/build/memory.out",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${workspaceFolder}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "gdb",
      "setupCommands": [
        {
          "description": "Enable pretty-printing for gdb",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ]
    },
    {
      "name": "Memory",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/build/memory_test.out",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${workspaceFolder}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "gdb",
      "setupCommands": [
        {
          "description": "Enable pretty-printing for gdb",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ]
    }
  ]
}
```

## Going Further

### Versioning

[`standard-version`](https://github.com/conventional-changelog/standard-version) is an utility for versioning and [`CHANGELOG.md`](./CHANGELOG.md).


Install `yarn`.

```
sudo apt update
sudo apt install yarn
```

If you already don’t have Node.js installed on your system , the command above will install it. Those who are using nvm can skip the Node.js installation with:

```
sudo apt install --no-install-recommends yarn
```

Verfy it with

```
yarn --version
```

#### Project Package

You will see a `package.json` file containing the following:

```json
{
	"name": "so-starter",
	"version": "1.1.0",
	"description": "A description",
	"repository": "https://github.com/tomasanchez/so-starter.git",
 	"author": "Tomas <tosanchez@frba.utn.edu.ar>",
}
```

You should modify the `"name"` to your project name. `"version"` should be "0.0.1", `"repository"` to your project repository. And `"author"` to your contact information.

This allows you the following scripts.

**NOTE**: You should remove the [`CHANGELOG`](./CHANGELOG.md) file before running the `first-release` script.

`yarn release:first-release` Will be your first release and will create a new git tag with the name `v.0.0.1`.

`yarn release:patch`: Will bump your version to `X.Y.+1` - use `patch` when fixing bugs.

`yarn release:minor`: Will bump your version to `X.+1.Z` - use `minor` when adding new features.

`yarn release:major`: Will bump your version to `+1.Y.Z` - use `major` when releasing breaking changes to previous versions.

#### Signature

To make use of this you will have to...

1. Install `gnupg2`:

```
sudo apt install gnupg2
```

2. Configure git to use `gnupg2`

```
git config --global gpg.program gpg2
```

3. Generate a `gpg` key

```
gpg --gen-key
```

#### Commiting

Recommended: read [this article](https://www.mokkapps.de/blog/how-to-automatically-generate-a-helpful-changelog-from-your-git-commit-messages/) about **semantic versions**, _conventional commits_, and using `standard-version`.

Conventional commit types [table with emojis](https://github.com/pvdlg/conventional-commit-types).

#### Commit types

[Source](https://github.com/pvdlg/conventional-commit-types).

Whenever you make changes, follow the [`convetional-commits`](https://www.conventionalcommits.org/en/v1.0.0/).

| Commit Type | Title                    | Description                                                                                                 | Emoji |
| ----------- | ------------------------ | ----------------------------------------------------------------------------------------------------------- | :---: |
| `feat`      | Features                 | A new feature                                                                                               |   ✨   |
| `fix`       | Bug Fixes                | A bug Fix                                                                                                   |   🐛   |
| `docs`      | Documentation            | Documentation only changes                                                                                  |   📚   |
| `style`     | Styles                   | Changes that do not affect the meaning of the code (white-space, formatting, missing semi-colons, etc)      |   💎   |
| `refactor`  | Code Refactoring         | A code change that neither fixes a bug nor adds a feature                                                   |   📦   |
| `perf`      | Performance Improvements | A code change that improves performance                                                                     |   🚀   |
| `test`      | Tests                    | Adding missing tests or correcting existing tests                                                           |   🚨   |
| `build`     | Builds                   | Changes that affect the build system or external dependencies (example scopes: gulp, broccoli, npm)         |   🛠   |
| `ci`        | Continuous Integrations  | Changes to our CI configuration files and scripts (example scopes: Travis, Circle, BrowserStack, SauceLabs) |   ⚙️   |
| `chore`     | Chores                   | Other changes that don't modify src or test files                                                           |   ♻️   |
| `revert`    | Reverts                  | Reverts a previous commit                                                                                   |   🗑   |


So when you run

`yarn release` there will be an automatically-generated changelog with your commit references.

There is also `yarn release:minor`, `yarn release:patch` and `yarn realease:major`. To follow the semantic versioning.

### Testing

Don't you taste your _guiso_ when you're cooking?

**Why do  we test?**

- Validate correct behavior
- Find bugs

> A good test **finds** bugs

This starter-pack includes a unit-test framework written in C/C++: [`CTEST`](https://github.com/bvdberg/ctest).


#### Implementation

Inside each project directory you will find the subdirectories of `src` and `test`.

The `test` directory contains a `core` subdirectory with a `test.c` file. You should avoid modifying the `core` directory at all. However, only for verbose and aesthetics you can change the `<MODULE_NAME>` for corresponding naming.

```c
int main(int argc, const char *argv[])
{
	printf("\033[0;35m");
	puts("# <MODULE_NAME> :: Tests");
	printf("\033[0m");

	return ctest_main(argc, argv);
}
```

Then you should define different test cases, in separate files. **RECOMMENDED**: use directories/file naming for the functionality tested.

In `client` we want to verify if the configuration file is being loaded. We provided a `config_init` function whith given a path, it opens a `.cfg` file, if it does, returns `SUCCESS` which is a `#define SUCCESS 1` or `ERROR` which is a `#define ERROR -1`.

Eg. from `client/test/common/config.c`.

```c
CTEST(config, when_configInit_does_init)
{
	// Are configurations UP?
	ASSERT_EQUAL(SUCCESS, config_init(CFG_FILE));
	config_close();
};
```

**NOTE**: the `CTEST` is provided by `ctest.h`, the first argument, in this case `config` is the suite of tests, while the second argument `when_configInit_does_init` is the test name. This will result in the following output (in case it does not fail) when running `make test`.

```
TEST Y/X config:when_configInit_does_init [OK]
```

Otherwise if it does fail:

```
TEST Y/X config:when_configInit_does_init [FAILED]
	ERR: config.c:Z expected 1, got -1
```

Remember that `SUCESS` expands to `1` meanwhile `ERROR` expands to `-1`.

#### Skipping tests

Instead of commenting out a test (and subsequently never remembering to turn it back on, ctest allows skipping of tests. Skipped tests are still shown when running tests, but not run. To skip a test add `_SKIP`:

```c
CTEST_SKIP(..)    or 	CTEST2_SKIP(..)
```

#### More complex tests

If you have coursed `Systems Design Course` you might have experience with `JUnit` testing for `Java`.

A test case with `setpup` abd `teardown` may resemble  `JUnit 5` anotattions `@BeforeEach` and `@AfterEach` respectively.

You can see an implementation examble in the `client` tests as described below.

```c
CTEST_DATA(client_send)
{
	conexion_t conexion;
};
```

We defined a `CTEST_DATA` for the _suite_ `client_send`. This means that every `CTEST(client_send, testname)` will have access to `data->conexion`.


```c
// @BeforeEach
CTEST_SETUP(client_send)
{
	data->conexion = conexion_cliente_create(HOSTNAME, PORT);
}
```

Before each `client_send` test, the `SETUP` behavior  will be executed. In this example it is used to instantiate a `conexion`.

```c
// @AfterEach
CTEST_TEARDOWN(client_send)
{
	if (&data->conexion)
		conexion_destroy(&data->conexion);
}
```

In c for each malloc, a corresponding free **MUST** be executed. After each `client_send` the `TEARDOWN` instructions will be executed.

With this, in our test cases we don't need to worry about creating and deleting objects, for this tests we use `CTEST2` instead of `CTEST`.

```c
CTEST2(client_send, when_clientSendNULL_then_isError)
{
	int result = on_client_send((void *)&data->conexion, NULL);
	ASSERT_EQUAL(ERROR, result);
}
```

For further information read the documentation on the [public repository](https://github.com/bvdberg/ctest).

## License

All material is provided under an MIT License unless otherwise specified.

MIT License: <https://mit-license.org/> or see the [`LICENSE`](https://github.com/tomasanchez/c-project/blob/master/LICENSE) file.

## Credits

This project has been facilitated with 💙 by [Tomás Sánchez](https://github.com/tomasanchez) & [Roberto Savinelli](https://github.com/rnsavinelli).
