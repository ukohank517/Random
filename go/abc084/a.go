package main

//参考ページ
//https://qiita.com/zurazurataicho/items/e66645bac16d9a482369
import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

// 文字列を1行入力
func StrStdin() (stringInput string) {
	scanner := bufio.NewScanner(os.Stdin)

	scanner.Scan()
	stringInput = scanner.Text()

	stringInput = strings.TrimSpace(stringInput)
	return
}

// 整数値1つ取得
func IntStdin() (int, error) {
	stringInput := StrStdin()
	return strconv.Atoi(strings.TrimSpace(stringInput))
}

func main() {
	i, err := IntStdin()
	if err != nil {
		fmt.Println(err)
	} else {
		fmt.Println(48 - i)
	}
}
