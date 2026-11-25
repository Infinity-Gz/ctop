# ctop

ctop is a Linux cgroup v2 fork of [htop 3.0.5](https://github.com/htop-dev/htop/tree/ce6d60e7def146c13d0b8bca4642e7401a0a8995), based on upstream commit `ce6d60e7def146c13d0b8bca4642e7401a0a8995`. The original interface, process tree, filtering, sorting, and process actions are inherited from htop.

```sh
ctop
ctop --cgroup /sys/fs/cgroup/path/to/container
ctop --cgroup path/to/container --tree
```

With no explicit target, ctop monitors the caller's cgroup and its descendants. An explicit target must be visible under the standard cgroup v2 mount at `/sys/fs/cgroup`. Process details require access to the corresponding PIDs in `/proc`.

- The aggregate CPU bar uses the target's cgroup CPU counters. Its denominator is the lowest readable CPU quota across the target and its ancestors, capped by the effective cpuset size when available. Each process's CPU% remains normalized to one logical CPU.
- Memory uses `memory.current`, including cache. The limit is the lowest readable `memory.max` across the target and its ancestors.
- The process list includes processes whose cgroup path is the target or a descendant. Configuration is saved to `~/.config/ctop/ctoprc` by default.

On Linux, install a C compiler, make, autoconf, automake, pkg-config, and ncurses development headers, then build and run:

```sh
cd htop
./autogen.sh
./configure
make
./htop
```

The build target keeps its upstream filename `htop`. Install that executable as `ctop` to use the examples above. The fork's source includes upstream copyright notices and the license in `htop/COPYING`.
