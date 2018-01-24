package ac

import (
	"fmt"
)

// Node ...
type Node struct {
	nextNode    map[byte]*Node
	failureNode *Node
	patternSet  []string
	ch          byte
	// nextSet     map[byte]interface{}
}

func (n *Node) String() string {
	next := make([]string, 0)
	for k := range n.nextNode {
		next = append(next, string(k))
	}
	return fmt.Sprintf("<Node: %s fail: %s patterns: %+v next: %v>", string(n.ch), string(n.failureNode.ch), n.patternSet, next)
}

// NewNode ...
func NewNode(ch byte) *Node {
	return &Node{
		nextNode:    make(map[byte]*Node),
		failureNode: nil,
		patternSet:  make([]string, 0),
		ch:          ch,
	}
}

// Matcher ...
type Matcher struct {
	root    *Node
	isBuilt bool
}

// NewMatcher ...
func NewMatcher() *Matcher {
	m := &Matcher{
		root: NewNode(0),
	}
	// root failure node is self
	m.root.failureNode = m.root
	return m
}

// AddPattern ...
func (m *Matcher) AddPattern(s string) {
	m.isBuilt = false
	i := 0
	l := len(s)
	cur := m.root

	for ; i < l; i++ {
		if _, ok := cur.nextNode[s[i]]; !ok {
			break
		}
		cur = cur.nextNode[s[i]]
	}

	for ; i < l; i++ {
		n := NewNode(s[i])
		cur.nextNode[s[i]] = n
		cur = n
	}
	cur.patternSet = append(cur.patternSet, s)
}

// BuildTransform ...
func (m *Matcher) BuildTransform() {
	queue := make([]*Node, 0)
	for _, v := range m.root.nextNode {
		v.failureNode = m.root
		queue = append(queue, v)
	}

	for len(queue) != 0 {
		curNode := queue[0]
		queue = queue[1:]

		for k, v := range curNode.nextNode {
			queue = append(queue, v)
			failureNode := curNode.failureNode

			// his is
			if t, ok := failureNode.nextNode[k]; ok && len(t.patternSet) != 0 {
				for _, j := range t.patternSet {
					v.patternSet = append(v.patternSet, j)
				}
			}

			if _, ok := failureNode.nextNode[k]; ok {
				v.failureNode = failureNode.nextNode[k]
			} else {
				v.failureNode = failureNode
			}
		}
	}
	m.isBuilt = true
}

// Match ...
func (m *Matcher) Match(s string) {
	if !m.isBuilt {
		m.BuildTransform()
	}

	cur := m.root
	for i := 0; i < len(s); i++ {
		if v, ok := cur.nextNode[s[i]]; ok {
			if len(v.patternSet) > 0 {
				fmt.Printf("found: %+v index: %d \n", v.patternSet, i)
			}
			cur = v
		} else if v, ok := cur.failureNode.nextNode[s[i]]; ok {
			if len(v.patternSet) > 0 {
				fmt.Printf("found: %+v index: %d \n", v.patternSet, i)
			}
			cur = v
		} else {
			cur = cur.failureNode
		}
	}
}
