package OOP2.Solution;

import OOP2.Provided.Person;
import OOP2.Provided.Status;

import java.util.ArrayList;

public class StatusImpl implements Status
{
	private final Integer mId;
	private final String mContent;
	private final Person mPublisher;
	private final ArrayList<Person> mLiked;

	/*
	 * A constructor that receives the status publisher, the text of the status
	 *  and the id of the status.
	 */
	public StatusImpl(Integer id, String content, Person publisher)
	{
		this.mId = id;
		this.mContent = content;
		this.mPublisher = publisher;
		this.mLiked = new ArrayList<>();
	}

	@Override
	public Integer getId()
	{
		return mId;
	}

	@Override
	public String getContent()
	{
		return mContent;
	}

	@Override
	public Person getPublisher()
	{
		return mPublisher;
	}

	@Override
	public void like(Person p)
	{
		if(mLiked.contains(p))
			return;
		mLiked.add(p);
	}

	@Override
	public void unlike(Person p)
	{
		mLiked.remove(p);
	}

	@Override
	public Integer getLikesCount()
	{
		return mLiked.size();
	}

	@Override
	public boolean equals(Object obj)
	{
		if(! (obj instanceof Status))
			return false;
		Status other = (Status) obj;
		return mId.equals(other.getId()) && mPublisher.equals(other.getPublisher());
	}
}
