package OOP2.Solution;

import OOP2.Provided.Status;
import OOP2.Provided.StatusIterator;

import java.util.Iterator;

public class StatusIteratorImpl implements StatusIterator
{
    Iterator<Status> statusIterator;

    public StatusIteratorImpl(Iterator<Status> statusIterator)
    {
        this.statusIterator = statusIterator;
    }

    @Override
    public boolean hasNext()
    {
        return statusIterator.hasNext();
    }

    @Override
    public Status next()
    {
        return statusIterator.next();
    }

    @Override
    public void remove()
    {
        StatusIterator.super.remove();
    }
}
