package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	stdin := bufio.NewScanner(os.Stdin)

	stdin.Scan()
	num := stdin.Text()

	A, _ := strconv.Atoi(strings.Split(num, " ")[0])
	B, _ := strconv.Atoi(strings.Split(num, " ")[1])

	stdin.Scan()
	str := stdin.Text()

	for i := 0; i < A+B+1; i++ {
		if i == A {
			if str[i] != '-' {
				fmt.Println("No")
				os.Exit(0)
			}
		} else {
			if (str[i] < '0') || (str[i] > '9') {
				fmt.Println("No")
				os.Exit(0)
			}
		}
	}

	fmt.Println("Yes")

}
