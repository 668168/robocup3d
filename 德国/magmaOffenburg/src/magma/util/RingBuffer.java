package magma.util;

/*************************************************************************
 *  Compilation:  javac RingBuffer.java
 *  Execution:    java RingBuffer
 *  
 *  Ring buffer (fixed size queue) implementation using a circular array
 *  (array with wrap-around).
 *
 *************************************************************************/

import java.util.Iterator;
import java.util.NoSuchElementException;

// suppress unchecked warnings in Java 1.5.0_6 and later
@SuppressWarnings("unchecked")
public class RingBuffer<Item> implements Iterable<Item>
{
	private final Item[] a; // queue elements

	private int N = 0; // number of elements on queue

	private int first = 0; // index of first element of queue

	private int last = 0; // index of next available slot

	// cast needed since no generic array creation in Java
	public RingBuffer(int capacity)
	{
		a = (Item[]) new Object[capacity];
	}

	public boolean isEmpty()
	{
		return N == 0;
	}

	public int size()
	{
		return N;
	}

	public void enqueue(Item item)
	{
		if (N == a.length) {
			throw new RuntimeException("Ring buffer overflow");
		}
		a[last] = item;
		last = (last + 1) % a.length; // wrap-around
		N++;
	}

	// remove the least recently added item - doesn't check for underflow
	public Item dequeue()
	{
		if (isEmpty()) {
			throw new RuntimeException("Ring buffer underflow");
		}
		Item item = a[first];
		a[first] = null; // to help with garbage collection
		N--;
		first = (first + 1) % a.length; // wrap-around
		return item;
	}

	public Iterator<Item> iterator()
	{
		return new RingBufferIterator();
	}

	// an iterator, doesn't implement remove() since it's optional
	private class RingBufferIterator implements Iterator<Item>
	{
		private int i = 0;

		public boolean hasNext()
		{
			return i < N;
		}

		public void remove()
		{
			throw new UnsupportedOperationException();
		}

		public Item next()
		{
			if (!hasNext())
				throw new NoSuchElementException();
			return a[i++];
		}
	}

	// a test client
	public static void main(String[] args)
	{
		RingBuffer<String> ring = new RingBuffer<String>(20);
		ring.enqueue("This");
		ring.enqueue("is");
		ring.enqueue("a");
		ring.enqueue("test.");

		for (String s : ring) {
			System.out.println(s);
		}

		System.out.println();

		while (!ring.isEmpty()) {
			System.out.println(ring.dequeue());
		}
	}

}
