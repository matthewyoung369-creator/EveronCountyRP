[ComponentEditorProps(
	category: "Everon County RP/Interaction",
	description: "Detects and exposes interactions available to the local player"
)]
// Registers the player interaction controller as an attachable script component.
class ECRP_PlayerInteractionControllerClass : ScriptComponentClass
{
}

// Detects the entity at the center of the active camera and caches its available
// ECRP interactions for future input and user-interface systems.
class ECRP_PlayerInteractionController : ScriptComponent
{
	protected float m_fMaximumInteractionDistance = 3.0;
	protected IEntity m_InteractionTarget;
	protected vector m_InteractionPosition;
	protected ref array<ref ECRP_InteractionAction> m_aAvailableActions = {};

	// Refreshes the current target and the actions available to this component's owner.
	// Returns true when at least one action is available.
	bool RefreshInteractions()
	{
		ClearInteractions();

		IEntity actor = GetOwner();

		if (!actor)
			return false;

		CameraManager cameraManager = GetGame().GetCameraManager();

		if (!cameraManager)
			return false;

		CameraBase camera = cameraManager.CurrentCamera();

		if (!camera)
			return false;

		vector interactionPosition;
		IEntity target = camera.GetCursorTargetWithPosition(interactionPosition);

		if (!target || target == actor)
			return false;

		if (vector.Distance(actor.GetOrigin(), interactionPosition) > m_fMaximumInteractionDistance)
			return false;

		if (!ECRP_InteractionService.GetInteractable(target))
			return false;

		m_InteractionTarget = target;
		m_InteractionPosition = interactionPosition;

		ECRP_InteractionService.GetAvailableInteractions(
			actor,
			m_InteractionTarget,
			m_aAvailableActions
		);

		return m_aAvailableActions.Count() > 0;
	}

	// Sets the maximum distance at which a target may be interacted with.
	void SetMaximumInteractionDistance(float distance)
	{
		if (distance <= 0)
			return;

		m_fMaximumInteractionDistance = distance;
	}

	// Returns the configured maximum interaction distance in meters.
	float GetMaximumInteractionDistance()
	{
		return m_fMaximumInteractionDistance;
	}

	// Returns the entity detected during the most recent refresh.
	IEntity GetInteractionTarget()
	{
		return m_InteractionTarget;
	}

	// Copies the actions from the most recent refresh into the supplied array.
	void GetAvailableInteractions(
		notnull array<ref ECRP_InteractionAction> availableActions)
	{
		availableActions.Clear();

		foreach (ECRP_InteractionAction action : m_aAvailableActions)
		{
			if (action)
				availableActions.Insert(action);
		}
	}

	// Returns the number of actions available after the most recent refresh.
	int GetAvailableInteractionCount()
	{
		return m_aAvailableActions.Count();
	}

	// Attempts an available interaction by its stable identifier.
	bool TryInteract(string interactionId)
	{
		if (!m_InteractionTarget)
			return false;

		IEntity actor = GetOwner();

		if (!actor)
			return false;

		if (vector.Distance(actor.GetOrigin(), m_InteractionPosition) > m_fMaximumInteractionDistance)
			return false;

		if (!FindAvailableInteraction(interactionId))
			return false;

		return ECRP_InteractionService.TryInteract(
			actor,
			m_InteractionTarget,
			interactionId
		);
	}

	// Clears the cached target and actions.
	void ClearInteractions()
	{
		m_InteractionTarget = null;
		m_aAvailableActions.Clear();
	}

	// Finds a cached available action by its stable identifier.
	protected ECRP_InteractionAction FindAvailableInteraction(string interactionId)
	{
		if (interactionId.IsEmpty())
			return null;

		foreach (ECRP_InteractionAction action : m_aAvailableActions)
		{
			if (action && action.GetInteractionId() == interactionId)
				return action;
		}

		return null;
	}
}
