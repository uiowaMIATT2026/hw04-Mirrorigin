## Experiment Analysis: CurvatureAD

The following combination achieves a balance between smoothing noise and preserving edge detail:

* **Conductance**: 2.5 (high enough to smooth out the noise within homogeneous tissue regions, but also low enough to stop diffusion at true anatomical boundaries).
* **Time Step**: 0.05 (keep small to ensure numerical stability during the 3D diffusion process).
* **Iterations**: 5 (enough iterations to allow the diffusion to propagate and clear the noise without over-processing the image).

Compared to the standard Gaussian LPF, this filter reduces noise while keeping the structural edges exceptionally sharp.