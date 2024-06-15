with import <nixpkgs> {};
(mkShell.override { stdenv = clangStdenv; }) {
  nativeBuildInputs = with pkgs; [ clang-tools llvmPackages_12.libllvm readline ];
}
