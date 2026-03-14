## Experiment Analysis: DOG

**Observation**:
- When using smaller values with a narrow difference (e.g., sigma1 = 1.0, sigma2 = 2.0), the DOG filter responds to high-frequency changes (highlighting fine details, sharp edges, but also some noise).
- When using larger values (e.g., sigma1 = 3.0, sigma2 = 5.0), the filter becomes sensitive to lower-frequency changes, suppressing noise and fine textures, and extracting thicker, prominent structural boundaries. The overall scale of the detected edges is directly proportional to the size of the sigma parameters selected.