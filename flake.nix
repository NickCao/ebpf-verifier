{
  inputs = {
    nixpkgs.url = "github:NickCao/nixpkgs/nixos-unstable-small";
    flake-utils.url = "github:numtide/flake-utils";
    radix_tree = {
      url = "github:ytakano/radix_tree/2fafde681c9580262795071c81c0576cb077e7e9";
      flake = false;
    };
    elfio = {
      url = "github:serge1/ELFIO/028b4117fafdab46b171473eebba9cccaa05e602";
      flake = false;
    };
    etl = {
      url = "github:ETLCPP/etl";
      flake = false;
    };
  };
  outputs = { self, nixpkgs, flake-utils, radix_tree, elfio, etl }:
    flake-utils.lib.eachDefaultSystem
      (system:
        let
          pkgs = import nixpkgs { inherit system; };
        in
        rec {
          packages = rec {
            ebpf-verifier = pkgs.stdenv.mkDerivation {
              name = "ebpf-verifier";
              src = self;
              nativeBuildInputs = with pkgs; [ cmake ];
              buildInputs = with pkgs; [ boost ];
              postPatch = ''
                ln -s ${radix_tree} external/radix_tree
                ln -s ${elfio} external/ELFIO
                ln -s ${etl} external/etl
              '';
            };
          };
        }
      );
}
