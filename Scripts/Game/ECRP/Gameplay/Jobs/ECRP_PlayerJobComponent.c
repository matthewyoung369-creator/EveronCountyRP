[ComponentEditorProps(
	category: "Everon County RP/Jobs",
	description: "Stores the player's currently active job"
)]
class ECRP_PlayerJobComponentClass : ScriptComponentClass
{
}

class ECRP_PlayerJobComponent : ScriptComponent
{
	protected static const string DELIVERY_DRIVER_JOB_ID = "delivery_driver";
	protected string m_sActiveJobId;
	protected bool m_bDeliveryPackagePickedUp;

	string GetActiveJobId()
	{
		return m_sActiveJobId;
	}

	bool HasActiveJob()
	{
		return !m_sActiveJobId.IsEmpty();
	}

	bool HasJob(string jobId)
	{
		if (jobId.IsEmpty())
			return false;

		return m_sActiveJobId == jobId;
	}

	bool AssignJob(string jobId)
	{
		if (jobId.IsEmpty() || jobId != DELIVERY_DRIVER_JOB_ID || HasActiveJob())
			return false;

		m_sActiveJobId = jobId;
		m_bDeliveryPackagePickedUp = false;
		return true;
	}

	bool IsDeliveryPackagePickedUp()
	{
		return m_bDeliveryPackagePickedUp;
	}

	bool MarkDeliveryPackagePickedUp()
	{
		if (!HasJob(DELIVERY_DRIVER_JOB_ID) || m_bDeliveryPackagePickedUp)
			return false;

		m_bDeliveryPackagePickedUp = true;
		return true;
	}

	void ClearActiveJob()
	{
		m_sActiveJobId = string.Empty;
		m_bDeliveryPackagePickedUp = false;
	}
}
