import os
import shutil
from pathlib import Path

# Caminhos do usuário
downloads_path = Path.home() / "Downloads"
documents_path = Path.home() / "Documents"
remapy_path = documents_path / "remapy"

# Garante que a pasta remapy exista
remapy_path.mkdir(parents=True, exist_ok=True)

# Lista todos os arquivos na pasta Downloads
download_files = [f for f in downloads_path.iterdir() if f.is_file()]

if not download_files:
    print("Nenhum arquivo encontrado na pasta Downloads.")
else:
    for file in download_files:
        extension = file.suffix.lower()

        if not extension:
            print(f"[Ignorado] Arquivo '{file.name}' não possui extensão.")
            continue

        # Caminho da subpasta com nome da extensão
        target_folder = remapy_path / extension
        target_folder.mkdir(exist_ok=True)

        # Caminho final do arquivo
        target_path = target_folder / file.name

        try:
            shutil.move(str(file), str(target_path))
            print(f"[Movido] '{file.name}' → '{target_folder}'")
        except Exception as e:
            print(f"[Erro] Falha ao mover '{file.name}': {e}")
