{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    cmake
    gcc
    gnumake
    pkgs.raylib
    pkgs.libGL
    xorg.libX11
  ];
}