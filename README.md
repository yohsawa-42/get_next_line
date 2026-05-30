*This project has been created as part of the 42 curriculum by yohsawa.*

# get_next_line

## Description

`get_next_line` は、ファイルディスクリプタから1行ずつ文字列を読み取る関数を実装する42カリキュラムの課題です。

標準ライブラリの高水準な入出力関数に頼らず、`read()`、静的変数、動的メモリ確保を使って、呼び出されるたびに次の1行を返します。返される文字列には、行末に改行文字が存在する場合はその `\n` も含まれます。EOFに到達し、返す文字がない場合は `NULL` を返します。

このリポジトリには通常版とbonus版があります。

- 通常版: 1つのstatic bufferで、1つのファイルディスクリプタを順に処理します。
- bonus版: ファイルディスクリプタごとにstatic bufferを持ち、複数fdを交互に読み進められます。

## Instructions

この課題はライブラリ関数として使う想定です。`main()` は提出ファイルには含めず、必要に応じてテスト用ファイルから呼び出します。

通常版のコンパイル例:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
  get_next_line/get_next_line.c \
  get_next_line/get_next_line_utils.c \
  your_main.c
```

bonus版のコンパイル例:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
  get_next_line/get_next_line_bonus.c \
  get_next_line/get_next_line_utils_bonus.c \
  your_main.c
```

使用例:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("sample.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

`BUFFER_SIZE` はコンパイル時に `-D BUFFER_SIZE=<size>` で指定できます。未指定の場合はヘッダ側のデフォルト値が使われます。

## Algorithm

この実装では、「読み込み済みだが、まだ返していない文字列」をstatic変数に保存します。`get_next_line()` が呼ばれるたびに、以下の流れで1行を作ります。

1. static bufferに改行文字 `\n` が含まれるまで、またはEOFに到達するまで `read()` で読み込みます。
2. 読み込んだ一時bufferをstatic bufferの末尾に連結します。
3. static bufferの先頭から、改行文字を含む1行分を切り出して返却用文字列にします。
4. 返却した行の後ろに残った文字列を、次回呼び出し用のstatic bufferとして保存します。
5. EOFに到達し、static bufferにも文字が残っていなければ `NULL` を返します。

この方式を選んだ理由は、`read()` が常に行単位で返してくれるわけではないためです。`BUFFER_SIZE` が行の長さより小さい場合、1行を作るには複数回の `read()` が必要です。逆に、`BUFFER_SIZE` が大きい場合は1回の `read()` で次の行の一部まで読み込むことがあります。そのため、余った文字列をstatic bufferに保存する設計が必要になります。

通常版ではstatic変数を1つだけ持ちます。bonus版では `static char *line[1024]` のようにfdごとに保存領域を分けることで、複数のファイルディスクリプタを交互に読んでも、それぞれの未返却部分を失わないようにしています。

エラー処理では、`read()` が `-1` を返した場合にstatic bufferも解放します。これは、読み込みエラー後に古い未返却文字列が残ると、次回呼び出しの結果が壊れたり、メモリリークにつながったりするためです。

## Files

- `get_next_line/get_next_line.c`: 通常版の本体
- `get_next_line/get_next_line_utils.c`: 通常版の補助関数
- `get_next_line/get_next_line.h`: 通常版のヘッダ
- `get_next_line/get_next_line_bonus.c`: bonus版の本体
- `get_next_line/get_next_line_utils_bonus.c`: bonus版の補助関数
- `get_next_line/get_next_line_bonus.h`: bonus版のヘッダ

## Resources

参考にした基本資料:

- `man 2 read`: `read()` の戻り値、EOF、エラー時の挙動
- `man 2 open`: ファイルディスクリプタの取得方法
- `man 2 close`: ファイルディスクリプタの解放方法
- `man 3 malloc`: 動的メモリ確保
- `man 3 free`: 動的メモリ解放
- 42 subject: get_next_line project requirements

AIの使用について:

- READMEの構成整理と日本語文面の作成にAIを使用しました。
- `get_next_line` のアルゴリズム説明、コンパイル例、メモリ管理上の注意点を文章化するためにAIを使用しました。
- 実装方針の確認として、EOF時の `NULL` 返却、`read()` エラー時のstatic buffer解放、bonus版のfd別static bufferについてAIと確認しました。
- 最終的なコードの責任、動作確認、提出判断は作成者が行います。
