with import <nixpkgs> {};
(mkShell.override { stdenv = clangStdenv; }) {
  nativeBuildInputs = with pkgs; [ clang-tools readline llvmPackages_12.libllvm ];
}
