import os

def generate_markdown(root_dir, exclude_dirs, exclude_files, exclude_extensions):
    markdown = ""
    for root, dirs, files in os.walk(root_dir, topdown=True):
        level = root.replace(root_dir, '').count(os.sep)
        indent = ' ' * 2 * (level)
        dirname = os.path.basename(root)
        dirs[:] = [d for d in dirs if d not in exclude_dirs]
        if dirname in exclude_dirs:
            continue
        markdown += '{}## {}\n'.format(indent, dirname)
        subindent = ' ' * 2 * (level + 1)
        for f in files:
            file_extension = os.path.splitext(f)[1]
            if f not in exclude_files and file_extension not in exclude_extensions:
                markdown += '{}### {}\n'.format(subindent, f)
                try:
                    with open(os.path.join(root, f), 'r', encoding='gb2312') as file:
                        code = file.read()
                        markdown += '```cpp\n' + code + '\n```\n'
                except UnicodeDecodeError:
                    markdown += '```cpp\n' + 'Cannot decode file content.' + '\n```\n'
                except PermissionError:
                    pass
    return markdown

exclude_dirs = ['.vs', '.idea', '.git', 'x64']
exclude_files = ['.gitattributes', '.gitignore']
exclude_extensions = ['.sln', '.vcxproj', '.filters', '.user', '.md']
markdown = generate_markdown('.\\', exclude_dirs, exclude_files, exclude_extensions)
with open('output.md', 'w', encoding='utf-8') as f:
    f.write(markdown)