{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
  };

  outputs = { self, nixpkgs }: {
    packages = nixpkgs.lib.genAttrs [ "x86_64-linux" ] (system:
    let
      pkgs = import nixpkgs { inherit system; };
    in
    rec {
      portifolio-server = pkgs.stdenv.mkDerivation {
        pname = "portifolio-server";
        version = "1.0.0";

        src = ./.;

        nativeBuildInputs = with pkgs; [ 
          clang 
          gnumake
        ];

        buildInputs = with pkgs; [ 
          clang-tools
        ];

        buildPhase = '' 
          make -f src/Makefile BUILD_DIR="$TMPDIR/build"

          runHook postBuild
        '';

        installPhase = ''
          runHook preInstall

          mkdir -p $out/bin
          mv $TMPDIR/build/portifolio-server $out/bin/
        '';
      };
    });

    defaultPackage = {
      x86_64-linux = self.packages.x86_64-linux.portifolio-server;
    };
  };
}
