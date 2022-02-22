# C Project Template

This folder contains a [`makefile`](./Makefile) which by defaults builds a `C` project using `GCC` which has the following structure

```
project
│   README.md
│   Makefile
│
└───src
│   │
│   └─ app
│   │  main.c
│   │
│   └─ folder
│   |  *.c
│   └─ another_folder
│       *.c
│
└───include
│   │
│   └─ folder
│       *.h
│    *.h
│
└───log
|   *.log
|
└───build
    *.out
```

## Commands

- **all**: `make` rule runs `comipile` and `run`
- **compile**: `make compile` compiles source files
- **run**: `make run` executes the program
- **leaks**: `make leaks` runs `compile` and runs the program in Valgrind, loggin the result in `log/leaks.log`
- **threads**: `make threads` runs `compile` and runs the program in Valgrind with the tool `Hellgrind`
- **clean**: deletes executable
- **cleanLogs**: deletes the `log` folder
- **remove**: runs `clean` and `cleanLogs`

## Getting Started

1. Create a repository from this template
2. If you don't have yarn , install it.

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

3. Inside the directory, run `yarn install`.
4. Run the make file using `make` or `yarn start`.

## Commiting

This project is configurated to use [`standard-version`](https://github.com/conventional-changelog/standard-version) which automaticly generates a [`CHANGELOG.md`](./CHANGELOG.md).

Recommended: read [this article](https://www.mokkapps.de/blog/how-to-automatically-generate-a-helpful-changelog-from-your-git-commit-messages/) about **semantic versions**, _conventional commits_, and using `standard-version`.

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

4. Whenever you make changes, follow the [`convetional-commits`](https://www.conventionalcommits.org/en/v1.0.0/)

5. run `yarn release`

There is also `yarn release:minor`, `yarn release:patch` and `yarn realease:major`. To follow the semantic versioning.

## License

All material is provided under an MIT License unless otherwise specified.

MIT License: <https://mit-license.org/> or see the [`LICENSE`](https://github.com/tomasanchez/c-project/blob/master/LICENSE) file.

## Credits

This project has been facilitated with 💙 by [Tomás Sánchez](https://github.com/tomasanchez).
