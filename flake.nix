{
  description = "qmk firmware flake";
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    treefmt-nix = {
      url = "github:numtide/treefmt-nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    git-hooks = {
      url = "github:cachix/git-hooks.nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };
  outputs =
    {
      self,
      nixpkgs,
      treefmt-nix,
      git-hooks,
      ...
    }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };

      check-qmk-exist = ''
        if ! [ -x "$(command -v qmk )" ]; then
          echo 'Error: qmk is not installed.' >&2
          exit 1
        fi
      '';
      keyboard-factory =
        {
          keyboard,
          keymap,
        }:
        pkgs.symlinkJoin rec {
          name = pkgs.lib.replaceStrings [ "/" ] [ "-" ] "${keyboard}-${keymap}";
          # bracket is necessary to coerce the builder function to the path
          paths = [
            (pkgs.writeScriptBin "build-${name}" (
              check-qmk-exist + ''qmk compile -kb ${keyboard} -km ${keymap} -j $NIX_BUILD_CORES''
            ))
            (pkgs.writeShellScriptBin "flash-${name}" (
              check-qmk-exist + ''qmk flash -kb ${keyboard} -km ${keymap} -j $NIX_BUILD_CORES''
            ))
          ];
        };
    in
    {
      checks.${system}.default = git-hooks.lib.${system}.run {
        src = ./.;
        hooks = {
          deadnix.enable = true;
          nixfmt-rfc-style.enable = true;
          statix = {
            enable = true;
            settings.config = "./statix.toml";
            settings.format = "stderr";
          };
        };
      };
      formatter.${system} = treefmt-nix.lib.mkWrapper nixpkgs.legacyPackages.x86_64-linux {
        projectRootFile = "flake.nix";
        # see for more options https://flake.parts/options/treefmt-nix
        programs.nixfmt.enable = true;
      };
      # TODO: add package. for pure firmware build using qmk setup & qmk doctor in buildphase

      devShells.${system}.default = pkgs.mkShell {
        name = "qmk";
        shellHook = ''
          ${self.checks.${system}.default.shellHook}
          qmk setup -y
          echo -e "type \033[0;32mbuild-keyboard-keymap\033[0m or \033[0;32mflash-keyboard-keymap\033[0m to build and flash the keyboard firmware respectively"
        '';
        packages = [
          self.checks.${system}.default.enabledPackages
          # NOTE: qmk is missing appdir in this repo commit
          (pkgs.qmk.overrideAttrs (oldAttrs: {
            propagatedBuildInputs = oldAttrs.propagatedBuildInputs ++ [ pkgs.python3.pkgs.appdirs ];
          }))
          (keyboard-factory {
            keyboard = "ploopyco/madromys";
            keymap = "via";
          })
          (keyboard-factory {
            keyboard = "ploopyco/trackball/rev1_007";
            keymap = "via";
          })
          (keyboard-factory {
            keyboard = "iv_works/av4_hotswap";
            keymap = "via";
          })
          (keyboard-factory {
            keyboard = "toffee_studio/blueberry";
            keymap = "via";
          })
          (keyboard-factory {
            keyboard = "sofleplus";
            keymap = "via";
          })
        ];
      };
    };
}
