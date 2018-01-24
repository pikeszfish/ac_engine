package main

import (
	"fmt"
	"io/ioutil"

	"github.com/pikeszfish/ac_engine/ac"
)

func main() {
	fmt.Println("Hello World!")
	patterns := []string{
		"her",
		"hers",
		"his",
		"she",
		"is",
	}
	matcher := ac.NewMatcher()
	for _, v := range patterns {
		matcher.AddPattern(v)
	}
	// matcher.Show()
	matcher.BuildTransform()

	filename := "./text-0.txt"
	text, err := ioutil.ReadFile(filename)
	if err != nil {
		fmt.Printf("shit happens, %+v \n", err)
	}

	matcher.Match(string(text))
}
