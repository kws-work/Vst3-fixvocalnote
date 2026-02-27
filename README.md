# ARA2 VST3 人声音高曲线插件（原型）

这个仓库提供一个可构建的 VST3 插件原型：

- 目标格式：VST3
- 目标能力：ARA2 扩展（后续接入）
- 目标 UI：类似 Melodyne 的音高曲线显示（当前为 mock 曲线）

> 说明：完整、可商用的 ARA2 集成需要 Steinberg VST3 SDK + Celemony ARA SDK，并完成宿主兼容与授权流程。

## 当前已实现

- JUCE 插件工程（VST3）
- 基础 `AudioProcessor` 骨架
- 音高网格 + 曲线 UI 原型

## 构建

### 方式 A：自动下载 JUCE（默认）

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release -j
```

### 方式 B：使用本地 JUCE

```bash
cmake -S . -B build -DJUCE_DIR=/path/to/JUCE -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release -j
```

## 产物位置（Linux）

通常位于：

- `build/FixVocalNote_artefacts/Release/VST3/FixVocalNote.vst3`

## 下一步（建议）

1. 接入 ARA2 Document Controller
2. 分析线程做 F0 检测（YIN / pYIN / CREPE）
3. UI 增加音符块分割、编辑手势与 drift/modulation 叠层
4. 在 `processBlock` 做实时重采样或离线渲染
