package ac

import (
	"testing"
)

func TestNode(t *testing.T) {
	node := NewNode(byte(105))
	if node.ch != byte(105) {
		t.Error("NewNode error")
	}
}

// TestMatcher ...
// root - h - e - r - s
//    |   |
//    |   h - i - s
//    |
// root - s - h - e
// root - i - s
func TestMatcher(t *testing.T) {
	patterns := []string{
		"her",
		"hers",
		"his",
		"she",
		"is",
	}
	matcher := NewMatcher()
	for _, p := range patterns {
		matcher.AddPattern(p)
	}
	matcher.BuildTransform()

	queue := make([]*Node, 0)
	for _, v := range matcher.root.nextNode {
		queue = append(queue, v)
	}

	for len(queue) != 0 {
		cur := queue[0]
		queue = queue[1:]
		for _, v := range cur.nextNode {
			queue = append(queue, v)
		}
		t.Log(cur)
	}
}
