## Experiment Analysis: Gaussian LPF

**Observation 1**: As the sigma value increases, the noise in the image is reduced (smoother appearance). The filter suppresses high-frequency noise components.

**Observation 2**: There is a tradeoff.
- Larger sigma values cause some loss of image resolution and details. The boundaries between different tissues become blurred, and fine anatomical structures are disappeared.
- A smaller sigma preserves edges better but causes more noise. The choice of sigma depends on balancing the need for noise reduction against the necessity of preserving critical anatomical edges.