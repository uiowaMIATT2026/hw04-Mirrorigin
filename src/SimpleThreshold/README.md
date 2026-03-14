## Experiment Analysis: SimpleThreshold

**Observation 1**: Pixels with intensities between the `lowThreshold` and `highThreshold` are set to the `insideValue` (e.g., 255), while pixels outside this range are set to the `outsideValue` (e.g., 0).

**Observation 2**: This method is straightforward and fast, but also highly sensitive to image noise. When applied directly to raw medical images, it results in many isolated noisy pixels.