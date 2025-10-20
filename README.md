# [Zen - 2D Game Engine](https://zengameengine.github.io/Zen/annotated.html)

**Zen** is a lightweight, cross‑platform 2‑D engine built on **SDL 3**, **OpenGL**, **GLM**, and **Dear ImGui**.

<div align="left">
  <a href="https://github.com/ZenGameEngine/Zen">
  <img src="https://github.com/kris-perezz/kris-perezz/blob/e1d9d553aa138b4d88194d87d2b508a229a21b46/images/zen-gamedemo.png" width="40%"/>
</a>
</a>
  <a href="https://github.com/kris-perezz/particle-system-editor">
  <img src="https://github.com/kris-perezz/kris-perezz/blob/e1d9d553aa138b4d88194d87d2b508a229a21b46/images/zen-particles.png" width="40%"/>
</a>
  
> The game engine currently has a demo that shows a minimal endles runner game and a particle system editor.

![1 million particles](https://github.com/kris-perezz/kris-perezz/blob/959c7cf20ce60dc45cd32dc8c5d31c6c2540905a/assets/Zen-1millionParticles.gif)
  
>  **Performance:** Sustains ~236 FPS with 100K particles and ~31 FPS with 1M particles on an RX 7700 XT

---  

## 🚧 Project Status

Zen is currently **in active development**.  
Core systems such as the renderer abstraction, event dispatcher, and particle framework are functional,  
but features like the Vulkan backend, ECS integration, and editor tooling are still in progress.

---

## ✨ Current Features

- Cross-platform (Windows / Linux)

- Event-driven architecture: unified event representation and dispatch system

- Priority-ordered layer stack for modular runtime management

- Input system abstraction over SDL3 keyboard/mouse states

- Time utilities for frame delta and profiling

- Logging infrastructure built on spdlog

- Renderer abstraction layer decouples high-level drawing commands from backend implementations

- Orthographic and Perspective camera

- Batch rendering support for particles

[**Documentation**](https://zengameengine.github.io/Zen/annotated.html)
