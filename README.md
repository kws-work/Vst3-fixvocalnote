# ARA2 VST3 人声音高曲线插件（原型）

这个仓库提供一个**可落地的原型结构**：

- 目标格式：VST3
- 目标能力：ARA2 扩展（宿主可离线提供音频与时间轴上下文）
- 目标 UI：类似 Melodyne 的音高曲线编辑界面（当前为 mock 曲线渲染）

> 说明：完整、可商用的 ARA2 集成需要 Steinberg VST3 SDK + Celemony ARA SDK，并完成宿主兼容与授权流程。

## 目录结构

- `CMakeLists.txt`：JUCE 工程入口（启用 VST3）
- `source/PluginProcessor.*`：音频处理与参数
- `source/PluginEditor.*`：音高曲线 UI（当前绘制示意曲线与音高网格）

## 下一步（建议）

1. 接入 ARA2 文档控制器（Document Controller）
2. 在分析线程做 F0 检测（YIN / pYIN / CREPE）并缓存片段级 pitch points
3. UI 增加：
   - 音符块分割（note segmentation）
   - 音高 drift / modulation 叠层
   - 手势编辑（draw / split / glue / formant）
4. 导出/回放：在 processBlock 内根据编辑参数做实时重采样或离线渲染

## 构建（示意）

```bash
cmake -S . -B build -DJUCE_DIR=/path/to/JUCE
cmake --build build -j
```

