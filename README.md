# LTCore

![Github Workflow Status](https://img.shields.io/github/actions/workflow/status/ltecheroffical/LTCore/ltengine_build_and_test.yml?branch=dev)
![GitHub License](https://img.shields.io/github/license/ltecheroffical/LTCore)
![GitHub Release](https://img.shields.io/github/v/release/ltecheroffical/LTCore)

**LTCore** is an open-source game core written in C/C++. The engine has no UI, so interaction is direct via the API. Most components are modular and can be detached and used independently. This engine is designed to sit on frameworks and provide the other part of frameworks. The engine may become standalone soon.

---

## Game Cores vs. Normal Games

LTCore is designed to support both **game cores** and **normal games**, which have distinct differences:

- **Game cores**: Provided in a library format with an API for updates and output. Game cores are ideal for reusability across multiple projects, but they typically output raw pixels, which requires a headless renderer, as most graphics APIs aren't optimized for pixel-only output.

- **Normal games**: Distributed as executables (e.g., `.exe` files) that manage the window and render directly to the screen. All functionality is self-contained within the executable, which is the industry standard format for game distribution.

### Pros and Cons

#### Pros

| Game Cores                                                        | Normal Games                                                                      |
|-------------------------------------------------------------------|-----------------------------------------------------------------------------------|
| Easy to integrate into other projects                             | Industry standard                                                                 |
| Modular and reusable                                              | All functionality in a single executable                                          |
| Ideal for custom game engines or platforms                        | Can be optimized for specific hardware                                            |
| Flexible for updates and changes without rebuilding the whole game| More performance-optimized for a target system                                    |
| Simplifies testing/debugging individual components (e.g., AI)     | More control over system resources (e.g., memory)                                 |
| Good for multi-platform development                               | Self-contained, with no external dependencies                                     |

#### Cons

| Game Cores                                                        | Normal Games                                              |
|-------------------------------------------------------------------|-----------------------------------------------------------|
| Not optimized for out-of-the-box performance                      | Less modular and reusable across projects                 |
| May depend on third-party libraries or frameworks                 | Not easily transferable across projects                   |
| More complex setup with external dependencies                     | Reduced flexibility for modifications and extensions      |

*Initially, LTCore was designed to build game cores, but now it supports both architectures.*

---

## Branching Strategy

- **`main` Branch**: The stable branch, used for releases. This branch should always compile without warnings.
- **`dev` Branch**: The development branch, where experimental changes are introduced. It may be unstable.
- **`experiment` Branch**: This branch is where all things that may or may not work go to, do not expect stuff here to always compile.
- **Feature Branches**: Named using `feature/[feature-name]`. Commits should be prefixed with `feat: ` and may not always compile.
- **Fix Branches**: Named using `fix/[issue]`. These branches typically are susposed to be fix stuff, these branches may not always compile.

---

## Getting Started

Currently, the recommended approach is to clone the repository into a third-party directory and use CMake to add it as a subdirectory. Releases will be available after v1.0.0. There is markdown documents in some parts.



---

## Licensing

LTCore is licensed under the MIT License, allowing free use for both commercial and non-commercial projects.

