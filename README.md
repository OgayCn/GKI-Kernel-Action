### 自动构建6.1-LTS分支内核

> 本仓库仅支持 6.1.X 的GKI设备，[在此](https://source.android.com/docs/core/architecture/kernel/gki-release-builds?hl=zh-cn)查看您的设备是否支持

### 下载刷入
- 可以 [点击此处](https://github.com/OgayCn/GKI-Kernel-Action/releases) 下载本仓库编译的资源

- 下载Ak3.zip文件，然后使用 [SukiSU Ultra](https://github.com/ShirkNeko/SukiSU-Ultra) 刷入

### 支持
| 功能 | 说明 |
| --- | --- |
| [SukiSU Ultra](https://github.com/ShirkNeko/SukiSU-Ultra) | SUKISU |
| [SUSFS4](https://gitlab.com/simonpunk/susfs4ksu) | 在内核层面辅助KSU隐藏的功能补丁 |
| [BBR](https://blog.thinkin.top/archives/ke-pu-bbrdao-di-shi-shi-me) | TCP拥塞控制算法，使网络更快？ |
| [Wireguard](https://zh.wikipedia.org/wiki/WireGuard) | 参考左侧wiki链接 |
| [LZ4KD](https://github.com/ShirkNeko/SukiSU_patch/tree/main/other) | 听说是来自HUAWEI source的ZRAM算法，补丁由[云彩之枫](http://www.coolapk.com/u/24963680)移植 |
| Clang21 编译 | 使用谷歌最新Clang21编译器编译 |
