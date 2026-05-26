# FluffOS v2019 补丁

`build.sh` / `build_msys2.sh` 会自动按文件名顺序把这里的 `*.patch` 应用到 clone 下来的 `fluffos/` 目录上。

> 目录命名为 `patches/v2019/` 而不是 `patches/fluffos-v2019/`，是为了避开仓库根 `.gitignore` 里 `fluffos*` 这条会一并忽略子路径的规则。

## 已有补丁

### `0001-add-missing-stl-includes-for-gcc11.patch`

FluffOS `v2019` 分支已经几年没有维护了，里头有两个头文件依赖了 C++17 才标准化的 `std::optional` 等，但只通过其它 STL 头文件**间接**引入，没有显式 `#include`：

- `src/base/internal/tracing.h` 用了 `std::optional` / `std::string_view`
- `src/base/internal/lru_cache.h` 用了 `std::optional`

在 GCC 9 及以下，`<unordered_map>` / `<string>` 等头文件会顺带把 `<optional>` 拖进来；但在 **GCC 11+（Ubuntu 22.04 默认即 11）以及当前 MSYS2 工具链** 上，这些隐式包含被移除了，结果就是：

```
error: ‘std::optional’ has not been declared
error: ‘optional’ in namespace ‘std’ does not name a template type
```

本补丁只做最小改动：把缺失的 `#include <optional>` / `#include <string_view>` 显式加进去，不动任何业务逻辑。

## 何时可以删掉

- 上游 FluffOS 的 `v2019` 分支接受了同样的修复 PR 并合并；
- 或者本 LIB 决定迁移到 FluffOS `v2025` / `master`（届时要做的远不止这点改动）。

## 新增补丁的建议

- 文件名加 4 位数字前缀，确定执行顺序（如 `0002-xxx.patch`）。
- 用 `git diff` 在 fluffos 子目录里产出补丁，相对路径以 `src/...` 开头。
- 改动尽量小，仅做兼容性修补；功能性变更走上游 PR。
