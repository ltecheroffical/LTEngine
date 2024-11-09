# LTEngine

**LTEngine** is an open-source game engine written in C/C++. The engine has no UI, so interaction is direct via the API. Most components are modular and can be detached and used independently. Currently, the engine supports 2D.

---

## Game Cores vs. Normal Games

LTEngine is designed to support both **game cores** and **normal games**, which have distinct differences:

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
| Can be integrated with various rendering systems                  | Easier to distribute as a single file                                             |
| Simplifies testing/debugging individual components (e.g., AI)     | More control over system resources (e.g., memory)                                 |
| Good for multi-platform development                               | Self-contained, with no external dependencies                                     |

#### Cons

| Game Cores                                                        | Normal Games                                              |
|-------------------------------------------------------------------|-----------------------------------------------------------|
| Requires a headless renderer for pixel output                     | Fixed to specific system or platform                      |
| Raw pixel output can be inefficient                               | Harder to integrate with other systems                    |
| May need extra layers for rendering and system management         | Limited flexibility in customizability                    |
| Not optimized for out-of-the-box performance                      | Less modular and reusable across projects                 |
| May depend on third-party libraries or frameworks                 | Not easily transferable across projects                   |
| More complex setup with external dependencies                     | Reduced flexibility for modifications and extensions      |

*Initially, LTEngine was designed to build game cores, but now it supports both architectures.*

---

## Branching Strategy

- **`main` Branch**: The stable branch, used for releases. This branch should always compile without warnings.
- **`dev` Branch**: The development branch, where experimental changes are introduced. It may be unstable.
- **Feature Branches**: Named using `feature/[feature-name]`. Commits should be prefixed with `feat: ` and may not always compile.

---

## Road to v1.0.0

These features are planned for the first stable release:

- [ ] **Finite State Machine**: Enables states for entities (e.g., Idle, Alerted, Attacking).
- [ ] **GPU Renderer**: Built-in support for GPU rendering (e.g., Vulkan, OpenGL).
- [ ] **Font Loading/Rendering**: Loading custom fonts and rendering text.
- [x] **Asset Manager**: Centralized management for assets (images, text, sounds) from bundles or directories.
- [ ] **Localization**: Support for multiple languages by mapping keys (e.g., "ui/buttons/save") to text (e.g., "Save").
- [ ] **Physics Engine Support**: Compatibility with physics engines (e.g., Box2D).
- [ ] **Audio Engine Support**: Compatibility with audio engines (e.g., raudio, soloud).
- [ ] **More examples**: Examples that show users how to use the engine.
- [ ] **Documentation**: Documentation comments through out the engine's headers.

---

## In the Future

- [ ] **3D Support**: Although ambitious, 3D rendering support may be added in future versions.

---

## Getting Started

Currently, the recommended approach is to clone the repository into a third-party directory and use CMake to add it as a subdirectory. Releases will be available after v1.0.0.

---

## Licensing

LTEngine is licensed under the MIT License, allowing free use for both commercial and non-commercial projects.

