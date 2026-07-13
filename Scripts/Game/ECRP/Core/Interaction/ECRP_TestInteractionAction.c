class ECRP_TestInteractionAction : ECRP_InteractionAction
{
	void ECRP_TestInteractionAction()
	{
		m_sInteractionId = "ecrp_test";
		m_sDisplayName = "Test Interaction";
	}

	override void Interact(ECRP_InteractionContext context)
	{
		if (!context)
			return;

		Print(
			"ECRP: Test interaction executed successfully!",
			LogLevel.NORMAL
		);
	}
}
