// Interaction action used by a job board to accept the delivery driver job.
class ECRP_AcceptDeliveryDriverAction : ECRP_InteractionAction
{
	// Assigns the action identifier and display name.
	void Initialize()
	{
		SetInteractionData(
			"accept_delivery_driver",
			"Accept Delivery Driver Job"
		);
	}

	// Handles acceptance of the delivery driver job.
	override void Interact(ECRP_InteractionContext context)
	{
		if (!context)
			return;

		Print(
			"ECRP: Delivery Driver job accepted.",
			LogLevel.NORMAL
		);
	}
}
