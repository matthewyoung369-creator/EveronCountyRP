class ECRP_InteractionService
{
	static ECRP_InteractableComponent GetInteractable(IEntity target)
	{
		if (!target)
			return null;

		return ECRP_InteractableComponent.Cast(
			target.FindComponent(ECRP_InteractableComponent)
		);
	}

	static void GetAvailableInteractions(
		IEntity actor,
		IEntity target,
		notnull array<ref ECRP_InteractionAction> availableActions)
	{
		availableActions.Clear();

		ECRP_InteractableComponent interactable = GetInteractable(target);

		if (!interactable)
			return;

		ref array<ref ECRP_InteractionAction> registeredActions = {};
		interactable.GetInteractionActions(registeredActions);

		ref ECRP_InteractionContext context =
			new ECRP_InteractionContext(actor, target);

		if (!context.IsValid())
			return;

		foreach (ECRP_InteractionAction action : registeredActions)
		{
			if (action && action.CanInteract(context))
				availableActions.Insert(action);
		}
	}

	static bool TryInteract(
		IEntity actor,
		IEntity target,
		string interactionId)
	{
		ECRP_InteractableComponent interactable = GetInteractable(target);

		if (!interactable)
			return false;

		ECRP_InteractionAction action =
			interactable.FindInteractionAction(interactionId);

		if (!action)
			return false;

		ref ECRP_InteractionContext context =
			new ECRP_InteractionContext(actor, target);

		if (!context.IsValid())
			return false;

		if (!action.CanInteract(context))
			return false;

		action.Interact(context);
		return true;
	}
}