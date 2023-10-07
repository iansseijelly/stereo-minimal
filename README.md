# Stereo-Minimal

A minimal stereo algorithm playground for CoSMo Experiment setup. 

## Usage

Clone this repository, then run the scripts. 
```
git clone https://github.com/iansseijelly/stereo-minimal
cd stereo-minimal
./run_stereoBM.sh
```

## Purpose

This is meant to not confuse people. It is supposed to be minimalistic. 

### StereoBM

The vanilla classical implementation. It is fast, and the depth image quality is acceptable. I think it's biggest issue is that if you set block size to be big, then you loose fidelity; if you set it too small, it doesn't work as well. There is hardly any middle ground. But it is fast. 

### StereoSGBM

Better fidelity with more complex algorithm. Looks like it only supports single core? Fine for my setup, but kind of concerning. It is computationally intense and will be slow. 