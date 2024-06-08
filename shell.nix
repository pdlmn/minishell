with import <nixpkgs> {};
(mkShell.override { stdenv = llvmPackages_12.stdenv; }) {
  nativeBuildInputs = with pkgs; [ clang-tools readline ];
}
