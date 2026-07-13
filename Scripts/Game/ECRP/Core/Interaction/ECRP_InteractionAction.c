class ECRP_InteractionAction
{
	protected string m_sInteractionId;
	protected string m_sDisplayName;

	void SetInteractionData(string interactionId, string displayName)
	{
		m_sInteractionId = interactionId;
		m_sDisplayName = displayName;
	}

	string GetInteractionId()
	{
		return m_sInteractionId;
	}

	string GetDisplayName()
	{
		return m_sDisplayName;
	}

	bool CanInteract(ECRP_InteractionContext context)
	{
		if (!context)
			return false;

		return context.IsValid();
	}

	void Interact(ECRP_InteractionContext context)
	{
		Print(
			"ECRP: Base interaction has no implementation.",
			LogLevel.WARNING
		);
	}
}