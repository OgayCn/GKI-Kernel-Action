### 自动构建6.1-LTS分支内核

> 本仓库仅支持 6.1 内核的 GKI 设备，[在此](https://source.android.com/docs/core/architecture/kernel/gki-release-builds?hl=zh-cn)查看您的设备是否支持

### 下载刷入
- 可以 [点击此处](https://github.com/OgayCn/GKI-Kernel-Action/releases) 下载本仓库编译的资源
- 下载Ak3.zip文件，然后使用 [SukiSU Ultra](https://github.com/ShirkNeko/SukiSU-Ultra) 刷入

### 支持
| 功能 | 说明 |
| --- | --- |
| [SukiSU](https://github.com/ShirkNeko/SukiSU-Ultra) | SukiSU Ultra |
| [SUSFS](https://gitlab.com/simonpunk/susfs4ksu) | 在内核层面辅助KSU隐藏的功能补丁 |
| [BBR](https://blog.thinkin.top/archives/ke-pu-bbrdao-di-shi-shi-me) | 更优秀的TCP拥塞控制算法 |
| [Wireguard](https://zh.wikipedia.org/wiki/WireGuard) | 参考左侧 wiki 链接 |
| [LZ4KD](https://github.com/ShirkNeko/SukiSU_patch/tree/main/other) | HUAWEI 的 zram 算法，由[云彩之枫](https://github.com/yspbwx2010)移植 |
| [Mi-Patch](https://github.com/OgayCn/GKI-Kernel-Action) | 修复米系手机使用LTS分支带来的严重问题 |
| [Clang21](https://android.googlesource.com/platform/prebuilts/clang/host/linux-x86/+archive/refs/heads/main-kernel) | 使用谷歌最新Clang21编译器编译 |