{
  description = "RMS build environment";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-24.05";
  };

  outputs = { self , nixpkgs ,... }: let
    system = "x86_64-linux";
  in {
    devShells."${system}".default = let
      pkgs = import nixpkgs {
        inherit system;
      };
    in pkgs.mkShell {
      packages = with pkgs; [
        gtk4
        libadwaita
        gnome.adwaita-icon-theme
        pkg-config
        xmake
        clang-tools
        llvmPackages_18.clangUseLLVM
        wrapGAppsHook4
      ];
      shellHook = ''
        unset LD
      '';
    };
  };
}
